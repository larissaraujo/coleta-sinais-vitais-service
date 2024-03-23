# include <../lib/utils/DateUtils.h>

String getDateTime(time_t t) {
    // Formata time_t como "aaaa-mm-ddThh:mm:ssZ"
    if (t == 0) {
        return "N/D";
    } else {
        t += 0;
        struct tm *ptm;
        ptm = gmtime(&t);
        String s;
        s.reserve(20);
        s = ptm->tm_year + 1900;
        s += "-";
        if (ptm->tm_mon < 10) {
            s += "0";
        }
        s += ptm->tm_mon + 1;
        s += "-";
        if (ptm->tm_mday < 10) {
            s += "0";
        }
        s += ptm->tm_mday;
        s += "T";
        if (ptm->tm_hour < 10) {
            s += "0";
        }
        s += ptm->tm_hour;
        s += ":";
        if (ptm->tm_min < 10) {
            s += "0";
        }
        s += ptm->tm_min;
        s += ":";
        if (ptm->tm_sec < 10) {
            s += "0";
        }
        s += ptm->tm_sec;
        s += "Z";
        return s;
    }
}