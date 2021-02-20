
#include <Foundation/Foundation.h>
#include <pthread.h>

#include <ct/platform/osx/autorelease_pool.h>

static pthread_key_t  poolKey;
static pthread_once_t initOnceToken = PTHREAD_ONCE_INIT;

static void createAutoreleasePool(void)
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    pthread_setspecific(poolKey, pool);
}

void checkAutoreleasePool(void) {
 	pthread_once(&initOnceToken, createAutoreleasePool);
    if (pthread_getspecific(poolKey) == NULL)
    {
        createAutoreleasePool();
    }
}
