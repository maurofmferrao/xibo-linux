#include "MainLayout.hpp"
#include "utils/utilities.hpp"

#include "IRegion.hpp"
#include "IBackground.hpp"

#include "GtkOverlayWrapper.hpp"

const int MIN_WIDTH = 160;
const int MAX_WIDTH = 9999;
const int MIN_HEIGHT = 120;
const int MAX_HEIGHT = 9999;

MainLayout::MainLayout(int width, int height)
{
    m_handler = std::make_unique<GtkOverlayWrapper>();
    setSize(width, height);
}

MainLayout::MainLayout(int width, int height, std::shared_ptr<IOverlayWrapper> handler)
{
    m_handler = handler;
    setSize(width, height);
}

MainLayout::~MainLayout()
{
}

void MainLayout::addRegion(std::shared_ptr<IRegion> region)
{
    if(region)
    {
        m_handler->addChild(region->handler(), region->top(), region->left(), region->width(), region->height());
        m_regions.push_back(std::move(region));
    }
}

IRegion& MainLayout::region(size_t index)
{
    return *m_regions.at(index);
}

size_t MainLayout::regionsCount() const
{
    return m_regions.size();
}

IOverlayWrapper& MainLayout::handler()
{
    return *m_handler;
}

void MainLayout::show()
{
    m_handler->show();
    reorderRegions();
    if(m_background)
    {
        m_background->show();
    }
    for(auto&& region : m_regions)
    {
        region->show();
    }
}

void MainLayout::reorderRegions()
{
    std::sort(m_regions.begin(), m_regions.end(), [=](const auto& first, const auto& second){
        return first->zindex() < second->zindex();
    });

    for(size_t i = 0; i != regionsCount(); ++i)
    {
        //utils::get_logger().trace("zindex: {} id: {} order: {}", m_regions[i]->zindex(), m_regions[i]->id(), i);
        m_handler->reorderChild(m_regions[i]->handler(), static_cast<int>(i));
    }
}

void MainLayout::setBackground(std::shared_ptr<IBackground> background)
{
    // FIXME 100x100 layout and 1920x1080 background = crash
    if(background)
    {
        if(m_background)
        {
            m_handler->remove();
        }
        m_background = std::move(background);
        m_background->setSize(width(), height());
        m_handler->add(m_background->handler());
    }
}

IBackground& MainLayout::background()
{
    if(!m_background)
        throw std::runtime_error("No bacgkround set");

    return *m_background;
}

// NOTE
// add test with different layout and region width
// region should be less than layout
void MainLayout::setSize(int width, int height)
{
    if(width < MIN_WIDTH || width > MAX_WIDTH || height < MIN_HEIGHT || height > MAX_HEIGHT)
        throw std::runtime_error("Width or height is too small/large");

    m_handler->setSize(width, height);
    if(m_background)
    {
        m_background->setSize(width, height);
    }
    for(auto&& region : m_regions)
    {
        region->setSize(region->width(), region->height());
    }
}

int MainLayout::width() const
{
    return m_handler->width();
}

int MainLayout::height() const
{
    return m_handler->height();
}
