#ifndef STK_CONFIG_H
#define STK_CONFIG_H

#ifdef _MSC_VER
#ifdef STK_DLL
#ifdef STK_EXPORTING
#define STK_API __declspec(dllexport)
#else
#define STK_API __declspec(dllimport)
#endif
#else
#define STK_API   // ¾²Ì¬¿âÊ±Îª¿Õ
#endif
#else
#ifdef STK_DLL
#ifdef STK_EXPORTING
#define STK_API __attribute__((visibility("default")))
#else
#define STK_API
#endif
#else
#define STK_API
#endif
#endif

#endif