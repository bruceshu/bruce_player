/* CopyRight bruceshu shuhuan.bruce@gmail.com
* 版本：初稿 V1.0
* 描述：播放器 native 层接口函数
* 作者：shuhuan
* 时间：2019/9/24
*/


#define JNI_CLASS_PLAYER "bruce/simple_android_jni_c_demo/Player"

static JavaVM* g_jvm;

typedef struct player_fields_t {
    pthread_mutex_t mutex;
    jclass clazz;
} player_fields_t;
static player_fields_t g_clazz;


static BruceMediaPlayer *jni_set_media_player(JNIEnv* env, jobject thiz, BruceMediaPlayer *mp)
{
    pthread_mutex_lock(&g_clazz.mutex);

    IjkMediaPlayer *old = (IjkMediaPlayer*) (intptr_t) J4AC_IjkMediaPlayer__mNativeMediaPlayer__get__catchAll(env, thiz);
    if (mp) {
        ijkmp_inc_ref(mp);
    }
    J4AC_IjkMediaPlayer__mNativeMediaPlayer__set__catchAll(env, thiz, (intptr_t) mp);

    pthread_mutex_unlock(&g_clazz.mutex);

    // NOTE: ijkmp_dec_ref may block thread
    if (old != NULL ) {
        ijkmp_dec_ref_p(&old);
    }

    return old;
}

void Player_native_setup(JNIEnv *env, jobject thiz, jobject weak_this)
{
    BruceMediaPlayer *pBruceMP = mp_android_create(message_loop);
    if (!pBruceMP) {
        printf("[%s:%d] mp_android_create failed!\n", __func__, __LINE__);
    }

    
}

static JNINativeMethod g_methods[] = {
    { "_native_setup",          "(Ljava/lang/Object;)V", (void *) Player_native_setup },
    { "_native_release",        "()V", (void *) Player_native_release },
    { "_prepare",               "()V", (void *) Player_prepare },
    { "_start",                 "()V", (void *) Player_start },
    { "_pause",                 "()V", (void *) Player_pause },
    { "_stop",                  "()V", (void *) Player_stop },
    { "_setVolume",             "()V", (void *) Player_setVolume },
};


JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JNIEnv* env = NULL;
    
    g_jvm = vm;
    if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }
    assert(env != NULL);

    pthread_mutex_init(&g_clazz.mutex, NULL );

    IJK_FIND_JAVA_CLASS(env, g_clazz.clazz, JNI_CLASS_PLAYER);
    (*env)->RegisterNatives(env, g_clazz.clazz, g_methods, NELEM(g_methods) );

    return JNI_VERSION_1_4;
}




