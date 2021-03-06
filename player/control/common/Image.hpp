#pragma once

#include "control/common/Widget.hpp"

#include <gtkmm/image.h>

class Uri;

class Image : public Widget
{
public:
    Image(int width, int height);

    int width() const override;
    int height() const override;
    void setSize(int width, int height) override;

    void setColor(uint32_t hex_color_number);
    void loadFromFile(const Uri& uri, bool preserveAspectRatio);

    Gtk::Image& get() override;

private:
    Glib::RefPtr<const Gdk::Pixbuf> pixbuf() const;
    Glib::RefPtr<Gdk::Pixbuf> pixbuf();

private:
    Gtk::Image m_handler;

};
