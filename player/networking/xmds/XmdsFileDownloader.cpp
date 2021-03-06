#include "XmdsFileDownloader.hpp"
#include "XmdsRequestSender.hpp"

#include "common/Utils.hpp"

const std::size_t DEFAULT_CHUNK_SIZE = 524288;

XmdsFileDownloader::XmdsFileDownloader(XmdsRequestSender& xmdsSender) :
    m_xmdsSender(xmdsSender)
{
}

boost::future<XmdsResponseResult> XmdsFileDownloader::download(int fileId, const std::string& fileType, std::size_t fileSize)
{
    std::size_t fileOffset = 0;
    DownloadXmdsFilesResult results;

    while(fileOffset < fileSize)
    {
        std::size_t chunkSize = fileOffset + DEFAULT_CHUNK_SIZE >= fileSize ? fileSize - fileOffset : DEFAULT_CHUNK_SIZE;

        results.emplace_back(m_xmdsSender.getFile(fileId, fileType, fileOffset, chunkSize));

        fileOffset += chunkSize;
    }

    return boost::async([=, results = std::move(results)]() mutable {
        return combineAllChunks(results);
    });
}

XmdsResponseResult XmdsFileDownloader::combineAllChunks(DownloadXmdsFilesResult& results)
{
    std::string fileContent;
    for(auto&& future : results)
    {
        auto [error, result] = future.get();
        if(!error)
        {
            fileContent += Utils::fromBase64(result.base64chunk);
        }
        else
        {
            return {error, std::string{}};
        }
    }
    return {PlayerError{}, fileContent};
}
