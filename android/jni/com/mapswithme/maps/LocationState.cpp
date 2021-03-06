#include "Framework.hpp"

#include "../core/jni_helper.hpp"

#include "../platform/Platform.hpp"


location::State * GetLocationState()
{
  return g_framework->NativeFramework()->GetLocationState().get();
}

extern "C"
{
  JNIEXPORT void JNICALL
  Java_com_mapswithme_maps_LocationState_switchToNextMode(JNIEnv * env, jobject thiz)
  {
    android::Platform::RunOnGuiThreadImpl(bind(&location::State::SwitchToNextMode, GetLocationState()), false);
  }

  JNIEXPORT jint JNICALL
  Java_com_mapswithme_maps_LocationState_getLocationStateMode(JNIEnv * env, jobject thiz)
  {
    return GetLocationState()->GetMode();
  }

  void LocationStateModeChanged(location::State::Mode mode, shared_ptr<jobject> const & obj)
  {
    JNIEnv * env = jni::GetEnv();
    env->CallVoidMethod(*obj.get(), jni::GetJavaMethodID(env, *obj.get(), "onLocationStateModeChangedCallback", "(I)V"), static_cast<jint>(mode));
  }

  JNIEXPORT jint JNICALL
  Java_com_mapswithme_maps_LocationState_addLocationStateModeListener(JNIEnv * env, jobject thiz, jobject obj)
  {
    return GetLocationState()->AddStateModeListener(bind(&LocationStateModeChanged, _1, jni::make_global_ref(obj)));
  }

  JNIEXPORT void JNICALL
  Java_com_mapswithme_maps_LocationState_removeLocationStateModeListener(JNIEnv * env, jobject thiz, jint slotID)
  {
    GetLocationState()->RemoveStateModeListener(slotID);
  }

  JNIEXPORT void JNICALL
  Java_com_mapswithme_maps_LocationState_turnOff(JNIEnv * env, jobject thiz)
  {
    GetLocationState()->TurnOff();
  }

  JNIEXPORT void JNICALL
  Java_com_mapswithme_maps_LocationState_invalidatePosition(JNIEnv * env, jobject thiz)
  {
    android::Platform::RunOnGuiThreadImpl(bind(&location::State::InvalidatePosition, GetLocationState()), false);
  }
}
