#include "ns_geo_api.h"

#include "shared/geoip.hpp"

void geoapi_init()
{
    geoip::init();
}

void geoapi_deinit()
{
    geoip::deinit();
}

double geoapi_distance(const char *ip1, const char *ip2)
{
    geoip::location_t location1 = geoip::find(ip1);
    geoip::location_t location2 = geoip::find(ip2);

    return geoip::distance(location1, location2);
}
