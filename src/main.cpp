#include "TrafficLightSimulationWidget.h"

#include <QApplication>


int main(int argc, char** argv)
{
    QApplication qapp(argc, argv);

    TrafficLightSimulationWidget traffic_light_simulation_widget;
    traffic_light_simulation_widget.show();

    return qapp.exec();
}
