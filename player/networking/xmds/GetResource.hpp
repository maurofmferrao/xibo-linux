#pragma once

#include "Soap.hpp"
#include "BaseResponseParser.hpp"
#include "BaseRequestSerializer.hpp"

#include "common/Field.hpp"

namespace GetResource
{
    struct Result
    {
        std::string resource;
    };

    struct Request
    {
        Field<std::string> serverKey{"serverKey"};
        Field<std::string> hardwareKey{"hardwareKey"};
        Field<int> layoutId{"layoutId"};
        Field<std::string> regionId{"regionId"};
        Field<std::string> mediaId{"mediaId"};
    };
}

template<>
class Soap::RequestSerializer<GetResource::Request> : public BaseRequestSerializer<GetResource::Request>
{
public:
    RequestSerializer(const GetResource::Request& request);
    std::string string();

};

template<>
class Soap::ResponseParser<GetResource::Result> : public BaseResponseParser<GetResource::Result>
{
public:
    ResponseParser(const std::string& soapResponse);

protected:
    GetResource::Result doParse(const xml_node& node) override;

};
