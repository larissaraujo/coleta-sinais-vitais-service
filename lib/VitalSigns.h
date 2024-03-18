#ifndef VITAL_SIGNS
#define VITAL_SIGNS

namespace TEMPERATURE {
    const static char* code = "8310-5";
    const static char* display = "Body temperature";
    const static char* valueCode = "Cel";
    const static char* unit = "C";
}

namespace HEART_RATE {
    static constexpr auto& code = "8867-4";
    static constexpr auto& display = "Heart Rate";
    static constexpr auto& valueCode = "/min";
    static constexpr auto& unit = "beats/minute";
}

namespace OXIMETRY {
    static constexpr auto& code = "2708-6";
    static constexpr auto& display = "Oxygen saturation";
    static constexpr auto& valueCode = "%";
    static constexpr auto& unit = "%";
}

#endif