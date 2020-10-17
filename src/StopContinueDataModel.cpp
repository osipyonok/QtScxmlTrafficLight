#include "StopContinueDataModel.h"

StopContinueDataModel::StopContinueDataModel(tIsStoppedChecker i_is_stopped_checker,
                                             tIsLastRed i_is_last_red_checker,
                                             tIsLastYellow2Red i_is_last_yellow_to_red_checker,
                                             tIsLastYellow2Green i_is_last_yellow_to_green_checker,
                                             tIsLastGreen i_is_last_green_checker,
                                             QObject* ip_parent/* = nullptr*/)
    : QScxmlCppDataModel(ip_parent)
    , m_is_stopped_checker(i_is_stopped_checker)
    , m_is_last_red_checker(i_is_last_red_checker)
    , m_is_last_yellow_to_red_checker(i_is_last_yellow_to_red_checker)
    , m_is_last_yellow_to_green_checker(i_is_last_yellow_to_green_checker)
    , m_is_last_green_checker(i_is_last_green_checker)
{
}

bool StopContinueDataModel::_IsStopped() const
{
    return m_is_stopped_checker();
}

bool StopContinueDataModel::_IsRunning() const
{
    return !m_is_stopped_checker();
}

bool StopContinueDataModel::_IsLastRed() const
{
    return m_is_last_red_checker();
}

bool StopContinueDataModel::_IsLastYellow2Red() const
{
    return m_is_last_yellow_to_red_checker();
}

bool StopContinueDataModel::_IsLastYellow2Green() const
{
    return m_is_last_yellow_to_green_checker();
}

bool StopContinueDataModel::_IsLastGreen() const
{
    return m_is_last_green_checker();
}
