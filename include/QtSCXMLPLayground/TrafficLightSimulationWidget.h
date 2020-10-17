#pragma once

#include <QWidget>


class TrafficLightSimulationWidget : public QWidget
{
    Q_OBJECT

public:
    TrafficLightSimulationWidget(QWidget* ip_parent = nullptr);

private:
    enum class MainState
    {
        Red,
        Green,
    };
    MainState m_last_main_state = MainState::Red;
};
