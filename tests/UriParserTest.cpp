#include "UriParserTest.hpp"

#include "utils/uri/UriParser.hpp"
#include "utils/uri/UriParseError.hpp"

TEST_P(UriParserValidHttpTests, UriParser_ParseValidHttpUri_EqualsGivenUri)
{
    UriParser parser;
    auto uriToTest = parser.parse(GetParam().strUrl);

    ASSERT_EQ(uriToTest.scheme(), GetParam().scheme);
    ASSERT_EQ(uriToTest.host(), GetParam().host);
    ASSERT_EQ(uriToTest.hostType(), GetParam().hostType);
    ASSERT_EQ(uriToTest.port(), GetParam().port.value());
    ASSERT_EQ(uriToTest.path(), GetParam().path);
    ASSERT_EQ(uriToTest.string(), GetParam().strUrl);
}

INSTANTIATE_TEST_CASE_P(Suite, UriParserValidHttpTests, ::testing::ValuesIn(validHttpUris));

TEST_P(UriParserValidFileTests, UriParser_ParseValidFileUri_EqualsGivenUri)
{
    UriParser parser;
    auto uriToTest = parser.parse(GetParam().strUrl);

    ASSERT_EQ(uriToTest.scheme(), GetParam().scheme);
    ASSERT_EQ(uriToTest.host(), GetParam().host);
    ASSERT_EQ(uriToTest.hostType(), GetParam().hostType);
    ASSERT_EQ(uriToTest.path(), GetParam().path);
    ASSERT_EQ(uriToTest.string(), GetParam().strUrl);
}

INSTANTIATE_TEST_CASE_P(Suite, UriParserValidFileTests, ::testing::ValuesIn(validFileUris));

TEST_P(UriParserInvalidTests, UriParser_ParseInvalidUri_ThrowsUriParseError)
{
    UriParser parser;
    ASSERT_THROW(parser.parse(GetParam()), UriParseError);
}

INSTANTIATE_TEST_CASE_P(Suite, UriParserInvalidTests, ::testing::ValuesIn(invalidUrls));