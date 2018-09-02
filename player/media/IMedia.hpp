#pragma once

#include <string>
#include <memory>
#include <sigc++/signal.h>

#include <gtkmm/widget.h> // FIXME

class IMedia
{
public:
    enum class Render
    {
        HTML,
        Native
    };

    virtual ~IMedia() = default;

    virtual void stop() = 0;
    virtual void start() = 0;
    virtual void requestHandler() = 0;
    virtual bool isRunning() const = 0;
    virtual void setSize(int width, int height) = 0;
    virtual void startTimer() = 0;

    virtual void attachAudio(std::unique_ptr<IMedia> audio) = 0;
    virtual sigc::signal<void, Gtk::Widget&, int, int>& handlerRequested() = 0;
    virtual sigc::signal<void>& mediaTimeout() = 0;

    virtual int id() const = 0;
    virtual int width() const = 0;
    virtual int height() const = 0;
    virtual int duration() const = 0;
    virtual Render render() const = 0;
    virtual const std::string& uri() const = 0;

};
