#include "TrafficLightSimulationWidget.h"
#include "ui_TrafficLightUi.h"
#include "TrafficLightSimulationFSM.h"

#include "StopContinueDataModel.h"
#include "TrafficLightWidget.h"

#include <QCheckBox>
#include <QGridLayout>
#include <QTimer>

namespace
{
    constexpr auto MS_PER_EVENT = 3000;
}

TrafficLightSimulationWidget::TrafficLightSimulationWidget(QWidget* ip_parent)
    : QWidget(ip_parent)
{
    Ui::TrafficLightUI ui;
    ui.setupUi(this);

    auto p_layout = new QGridLayout(ui.mp_traffic_light_container);
    p_layout->setContentsMargins(0, 0, 0, 0);

    auto p_traffic_light = new TrafficLightWidget(ui.mp_traffic_light_container);
    p_layout->addWidget(p_traffic_light);
    
    auto p_timer = new QTimer(this);

    auto p_fsm = new TrafficLightSimulationFSM(this);
    auto p_data_model = new StopContinueDataModel([=] { return ui.mp_stop_checkbox->isChecked(); }, 
                                                  [=] { return p_traffic_light->GetState() == TrafficLightWidget::State::Red; },
                                                  [=] { return p_traffic_light->GetState() == TrafficLightWidget::State::Yellow && m_last_main_state == MainState::Green; },
                                                  [=] { return p_traffic_light->GetState() == TrafficLightWidget::State::Yellow && m_last_main_state == MainState::Red; },
                                                  [=] { return p_traffic_light->GetState() == TrafficLightWidget::State::Green; },
                                                  p_fsm);
    p_fsm->setDataModel(p_data_model);
    
    p_fsm->connectToState("Red", p_traffic_light, [=](bool i_active)
    {
        if (i_active)
        {
            p_traffic_light->SetState(TrafficLightWidget::State::Red);
            m_last_main_state = MainState::Red;
            ui.mp_log_list_widget->addItem("Entered Red state");
        }
    });
    p_fsm->connectToState("Green", p_traffic_light, [=](bool i_active)
    {
        if (i_active)
        {
            p_traffic_light->SetState(TrafficLightWidget::State::Green);
            m_last_main_state = MainState::Green;
            ui.mp_log_list_widget->addItem("Entered Green state");
        }
    });
    p_fsm->connectToState("Yellow2Green", p_traffic_light, [=](bool i_active)
    {
        if (i_active)
        {
            p_traffic_light->SetState(TrafficLightWidget::State::Yellow);
            ui.mp_log_list_widget->addItem("Entered Yellow->Green state");
        }
    });
    p_fsm->connectToState("Yellow2Red", p_traffic_light, [=](bool i_active)
    {
        if (i_active)
        {
            p_traffic_light->SetState(TrafficLightWidget::State::Yellow);
            ui.mp_log_list_widget->addItem("Entered Yellow->Red state");
        }
    });
    p_fsm->connectToState("Paused", p_timer, [=](bool i_active)
    {
        if (i_active)
        {
            ui.mp_log_list_widget->addItem("Paused");
            p_timer->stop();
        }
        else
        {
            ui.mp_log_list_widget->addItem("Started");
            p_timer->start(MS_PER_EVENT);
        }
    });

    connect(p_timer, &QTimer::timeout, p_fsm, [=]
    {
        p_fsm->submitEvent("OnTimeout");
    });
    connect(ui.mp_stop_checkbox, &QCheckBox::toggled, p_fsm, [=]
    {
        p_fsm->submitEvent("OnPauseClicked");
    });

    p_timer->start(MS_PER_EVENT);
    p_fsm->start();
}
