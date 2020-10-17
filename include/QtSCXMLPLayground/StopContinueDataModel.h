#pragma once

#include <QScxmlCppDataModel.h>

#include <functional>

class StopContinueDataModel : public QScxmlCppDataModel
{
    Q_OBJECT
    Q_SCXML_DATAMODEL

public:
    using tIsStoppedChecker = std::function<bool()>;
    using tIsLastRed = std::function<bool()>;
    using tIsLastYellow2Red = std::function<bool()>;
    using tIsLastYellow2Green = std::function<bool()>;
    using tIsLastGreen = std::function<bool()>;
    StopContinueDataModel(tIsStoppedChecker i_is_stopped_checker,
                          tIsLastRed i_is_last_red_checker,
                          tIsLastYellow2Red i_is_last_yellow_to_red_checker,
                          tIsLastYellow2Green i_is_last_yellow_to_green_checker,
                          tIsLastGreen i_is_last_green_checker,
                          QObject* ip_parent = nullptr);

private:
    bool _IsStopped() const;
    bool _IsRunning() const;

    bool _IsLastRed() const;
    bool _IsLastYellow2Red() const;
    bool _IsLastYellow2Green() const;
    bool _IsLastGreen() const;

    tIsStoppedChecker m_is_stopped_checker;
    tIsLastRed m_is_last_red_checker;
    tIsLastYellow2Red m_is_last_yellow_to_red_checker;
    tIsLastYellow2Green m_is_last_yellow_to_green_checker;
    tIsLastGreen m_is_last_green_checker;
};
