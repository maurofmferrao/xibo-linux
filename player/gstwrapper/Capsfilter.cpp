#include "Capsfilter.hpp"
#include "Caps.hpp"

Gst::Capsfilter::Capsfilter() :
    Gst::Element("capsfilter")
{
}

Gst::RefPtr<Gst::Capsfilter> Gst::Capsfilter::create()
{
    return std::shared_ptr<Gst::Capsfilter>(new Gst::Capsfilter);
}

void Gst::Capsfilter::setCaps(Gst::RefPtr<Gst::Caps> caps)
{
    m_caps = std::move(caps);
    g_object_set(element(), "caps", m_caps->getHandler(), nullptr);
}
