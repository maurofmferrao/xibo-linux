#include "constants.hpp"
#include "media/Image.hpp"
#include "creators/MediaFactory.hpp"
#include <memory>

class IMedia;

class ImageFactory : public MediaFactory
{
public:
    ImageFactory(const xlf_node& parentNode, const xlf_node& mediaNode);

protected:
    std::unique_ptr<IMedia> doCreate() override;

private:
    Image::ScaleType toScaleType(const std::string& scaleType);
    Image::Align toAlign(const std::string& align);
    Image::Valign toValign(const std::string& valign);

};
