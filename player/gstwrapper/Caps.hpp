#pragma once

#include "GstFwd.hpp"
#include <gst/gstcaps.h>
#include <string>

namespace Gst
{
    class Structure
    {
    public:
        Structure(GstStructure* handler);
        int getHeight() const;
        int getWidth() const;
        std::string getName() const;

    private:
        GstStructure* m_handler = nullptr;

    };

    class Caps
    {
    public:
        Caps(GstCaps* getHandler);
        Caps(std::string_view stringCaps);
        Caps(Caps&& other);
        Caps& operator=(Caps&& other);
        ~Caps();

        static Gst::RefPtr<Gst::Caps> create(std::string_view stringCaps);
        Gst::RefPtr<Gst::Structure> getStructure(guint index) const;
        GstCaps* getHandler();

    private:
        GstCaps* m_handler = nullptr;
    };
}
