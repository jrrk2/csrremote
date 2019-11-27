
#ifdef __cplusplus
extern "C" {
#else
  typedef _Bool bool;
#endif  
  int download(bool (*readblock)(uint16_t, int, uint16_t *),
               bool (*read)(uint16_t addr, uint16_t *data),
               bool (*writeblock)(uint16_t addr, int size, uint16_t buffer[]),
               bool (*write)(uint16_t addr, uint16_t data),
               bool (*_IsXAPStopped)(void),
               uint16_t writebuf[], int first, int last);
#ifdef __cplusplus
};
#endif  
