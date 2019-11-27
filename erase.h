
#ifdef __cplusplus
extern "C" {
#else
  typedef _Bool bool;
#endif  
  int erase(bool (*readblock)(uint16_t, int, uint16_t *),
            bool (*read)(uint16_t addr, uint16_t *data),
            bool (*writeblock)(uint16_t addr, int size, uint16_t buffer[]),
            bool (*write)(uint16_t addr, uint16_t data),
            bool (*_IsXAPStopped)(void));
#ifdef __cplusplus
};
#endif  
