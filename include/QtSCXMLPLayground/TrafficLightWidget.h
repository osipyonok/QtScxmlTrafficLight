#pragma once

#include <QWidget>


class TrafficLightWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(State state READ GetState WRITE SetState)

public:
    TrafficLightWidget(QWidget* ip_parent = nullptr);

    enum class State
    {
        Red,
        Yellow,
        Green
    };
    void SetState(State i_state);
    State GetState() const;

    void paintEvent(QPaintEvent* ip_event) override;

private:
    State m_state = State::Red;
};
