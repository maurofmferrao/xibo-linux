#include "RegisterDisplay.hpp"

#include "Resources.hpp"
#include "common/Utils.hpp"

namespace Resources = XmdsResources::RegisterDisplay;

Soap::RequestSerializer<RegisterDisplay::Request>::RequestSerializer(const RegisterDisplay::Request& request) : BaseRequestSerializer(request)
{
}

std::string Soap::RequestSerializer<RegisterDisplay::Request>::string()
{
    return createRequest(Resources::Name,
                         request().clientCode,
                         request().clientType,
                         request().clientVersion,
                         request().displayName,
                         request().macAddress,
                         request().xmrChannel,
                         request().xmrPubKey,
                         request().serverKey,
                         request().hardwareKey);

}

Soap::ResponseParser<RegisterDisplay::Result>::ResponseParser(const std::string& soapResponse) : BaseResponseParser(soapResponse)
{
}

RegisterDisplay::Result Soap::ResponseParser<RegisterDisplay::Result>::doParse(const xml_node& node)
{
    auto activationMessage = node.get<std::string>(Resources::ActivationMessage);
    auto display = Utils::parseXmlFromString(activationMessage).get_child(Resources::Display);
    auto attrs = display.get_child(Resources::DisplayAttrs);

    RegisterDisplay::Result result;
    result.status.code = static_cast<RegisterDisplay::Result::Status::Code>(attrs.get<int>(Resources::Status));
    result.status.message = attrs.get<std::string>(Resources::StatusMessage);
    if(result.status.code == RegisterDisplay::Result::Status::Code::Ready)
    {
        fillPlayerSettings(result.playerSettings, display);
    }

    return result;
}

void Soap::ResponseParser<RegisterDisplay::Result>::fillPlayerSettings(PlayerSettings& settings, const xml_node& display)
{
    namespace Settings = Resources::Settings;

    settings.collectInterval = display.get<int>(Settings::CollectInterval);
    settings.downloadStartWindow = display.get<std::string>(Settings::DownloadStartWindow);
    settings.downloadEndWindow = display.get<std::string>(Settings::DownloadEndWindow);
    settings.statsEnabled = display.get<bool>(Settings::StatsEnabled);
    settings.xmrNetworkAddress = display.get<std::string>(Settings::XmrNetworkAddress);
    settings.dimensions.width = static_cast<int>(display.get<double>(Settings::Width));
    settings.dimensions.height = static_cast<int>(display.get<double>(Settings::Height));
    settings.dimensions.x = static_cast<int>(display.get<double>(Settings::XPos));
    settings.dimensions.y = static_cast<int>(display.get<double>(Settings::YPos));
    settings.logLevel = toLogLevelEnum(display.get<std::string>(Settings::LogLevel));
    settings.shellCommandsEnabled = display.get<bool>(Settings::EnableShellCommands);
    settings.modifiedLayoutsEnabled = display.get<bool>(Settings::ExpireModifiedLayouts);
    settings.maxConcurrentDownloads = display.get<int>(Settings::MaxConcurrentDownloads);
    //shellCommandAllowList
    settings.statusLayoutUpdate = display.get<bool>(Settings::SendCurrentLayoutAsStatusUpdate);
    settings.screenshotInterval = display.get<int>(Settings::ScreenShotRequestInterval);
    settings.screenshotSize = display.get<int>(Settings::ScreenShotSize);
    settings.maxLogFilesUploads = display.get<int>(Settings::MaxLogFileUploads);
    settings.embeddedServerPort = display.get<int>(Settings::EmbeddedServerPort);
    settings.preventSleep = display.get<bool>(Settings::PreventSleep);
    settings.displayName = display.get<std::string>(Settings::DisplayName);
    settings.screenshotRequested = display.get<bool>(Settings::ScreenShotRequested);
}


LoggingLevel Soap::ResponseParser<RegisterDisplay::Result>::toLogLevelEnum(const std::string& level)
{
    if(level == "trace")
        return LoggingLevel::Trace;
    else if(level == "audit")
        return LoggingLevel::Debug;
    else if(level == "info")
        return LoggingLevel::Info;
    else if(level == "error")
        return LoggingLevel::Error;

    return LoggingLevel::Error;
}
