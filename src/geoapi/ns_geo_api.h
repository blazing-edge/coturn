#ifndef __GEO_API__
#define __GEO_API__

#ifdef __cplusplus
extern "C" {
#endif

void geoapi_init();

void geoapi_deinit();

double geoapi_distance(const char* ip1, const char* ip2);

#ifdef __cplusplus
}
#endif

#endif //__GEO_API__
