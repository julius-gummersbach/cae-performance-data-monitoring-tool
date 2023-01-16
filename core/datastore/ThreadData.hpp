#ifndef CAE_PERFORMANCE_DATA_MONITORING_TOOL_THREADDATA_H
#define CAE_PERFORMANCE_DATA_MONITORING_TOOL_THREADDATA_H


#include <string>

using std::string;

struct ThreadData {
    string m_name;
    bool m_isValid;

    [[nodiscard]] const string &getName() const;

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] double getSumRt() const;

    [[nodiscard]] double getMaxRt() const;

    [[nodiscard]] double getAvgRt() const;

    [[nodiscard]] double getSumVs() const;

    [[nodiscard]] double getSumIs() const;

    double m_sumRt;
    double m_maxRt;
    double m_avgRt;
    double m_sumVs;
    double m_sumIs;

    ThreadData(string name, bool isValid, double sumRt, double maxRt, double avgRt, double sumVs,
               double sumIs);
};


#endif //CAE_PERFORMANCE_DATA_MONITORING_TOOL_THREADDATA_H
