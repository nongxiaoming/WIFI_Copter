#ifndef __DRV_WIFI_H__
#define __DRV_WIFI_H__

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
	 
void wifi_lib_init(void);
void wifi_init(void);
void softAPModeStart(void);
void stationModeStart(void);
void wifi_tick(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
