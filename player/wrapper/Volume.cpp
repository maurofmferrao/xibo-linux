#include "Volume.hpp"

Gst::Volume::Volume()
{
    m_element = gst_element_factory_make("volume", nullptr);
}

Gst::RefPtr<Gst::Volume> Gst::Volume::create()
{
    return std::shared_ptr<Gst::Volume>(new Gst::Volume);
}

void Gst::Volume::setVolume(double volume)
{
    g_object_set(m_element, "volume", volume, nullptr);
}

double Gst::Volume::getVolume() const
{
    double volume;
    g_object_get(m_element, "volume", &volume, nullptr);
    return volume;
}
