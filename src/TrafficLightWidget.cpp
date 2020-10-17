#include "TrafficLightWidget.h"

#include <QPainter>
#include <QPalette>
#include <QPen>


TrafficLightWidget::TrafficLightWidget(QWidget* ip_parent)
    : QWidget(ip_parent)
{
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(Pal);
}

void TrafficLightWidget::SetState(State i_state)
{
    if (m_state == i_state)
        return;

    m_state = i_state;
    update();
}

TrafficLightWidget::State TrafficLightWidget::GetState() const
{
    return m_state;
}

void TrafficLightWidget::paintEvent(QPaintEvent* ip_event)
{
    auto height = size().height();
    auto width = size().width();

    auto vertical_offset = std::min(static_cast<int>(height * 0.05), 10);
    auto horizontal_offset = std::min(static_cast<int>(width * 0.05), 10);
    auto radius = std::min(static_cast<int>(((height - 2 * vertical_offset) - vertical_offset) / 6.),
                           static_cast<int>((width - 2 * horizontal_offset) / 2.));

    auto extra_vertical_space = std::max((height - 2 * vertical_offset - 6 * radius) / 6, 0);
    auto extra_horizontal_space = std::max((width - 2 * horizontal_offset - 2 * radius) / 2, 0);

    QPainter painter(this);

    auto color = GetState() == State::Red ? Qt::red : Qt::black;
    painter.setBrush(color);
    painter.setPen(color);
    painter.drawEllipse(horizontal_offset + extra_horizontal_space, vertical_offset + extra_vertical_space, 2 * radius, 2 * radius);

    color = GetState() == State::Yellow ? Qt::yellow : Qt::black;
    painter.setBrush(color);
    painter.setPen(color);
    painter.drawEllipse(horizontal_offset + extra_horizontal_space, vertical_offset + 3 * extra_vertical_space + 2 * radius, 2 * radius, 2 * radius);

    color = GetState() == State::Green ? Qt::green : Qt::black;
    painter.setBrush(color);
    painter.setPen(color);
    painter.drawEllipse(horizontal_offset + extra_horizontal_space, vertical_offset + 5 * extra_vertical_space + 4 * radius, 2 * radius, 2 * radius);
}
