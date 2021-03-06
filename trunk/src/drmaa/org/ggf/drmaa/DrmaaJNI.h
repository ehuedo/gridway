/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_ggf_gridway_drmaa_DrmaaJNI */

#ifndef _Included_DrmaaJNI
#define _Included_DrmaaJNI
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_ggf_drmaa_DrmaaJNI
 * Method:    init
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_ggf_drmaa_DrmaaJNI_init
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     org_ggf_drmaa_DrmaaJNI
 * Method:    exit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_ggf_drmaa_DrmaaJNI_exit
  (JNIEnv *, jobject);

/*
 * Class:     org_ggf_drmaa_DrmaaJNI
 * Method:    createJobTemplate
 * Signature: ()Lorg/ggf/gridway/drmaa/JobTemplate;
 */
JNIEXPORT jobject JNICALL Java_org_ggf_drmaa_DrmaaJNI_createJobTemplate
  (JNIEnv *, jobject);

/*
 * Class:     org_ggf_drmaa_DrmaaJNI
 * Method:    deleteJobTemplate
 * Signature: (Lorg/ggf/gridway/drmaa/JobTemplate;)V
 */
JNIEXPORT void JNICALL Java_org_ggf_drmaa_DrmaaJNI_deleteJobTemplate
  (JNIEnv *, jobject, jobject);

/*
 * Class:     org_ggf_drmaa_DrmaaJNI
 * Method:    runJob
 * Signature: (Lorg/ggf/gridway/drmaa/JobTemplateImpl)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_ggf_drmaa_DrmaaJNI_runJob
  (JNIEnv *, jobject, jobject);

/*
 * Class:     org_ggf_drmaa_DrmaaJNI
 * Method:    runBulkJobs
 * Signature: (Lorg/ggf/gridway/drmaa/JobTemplateImpl;III)Ljava/util/List;
 */
JNIEXPORT jobject JNICALL Java_org_ggf_drmaa_DrmaaJNI_runBulkJobs
  (JNIEnv *, jobject, jobject, jint, jint, jint);

/*
 * Class:     org_ggf_drmaa_DrmaaJNI
 * Method:    control
 * Signature: (Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_org_ggf_drmaa_DrmaaJNI_control
  (JNIEnv *, jobject, jstring, jint);

/*
 * Class:     org_ggf_drmaa_DrmaaJNI
 * Method:    synchronize
 * Signature: (Ljava/util/List;JZ)V
 */
JNIEXPORT void JNICALL Java_org_ggf_drmaa_DrmaaJNI_synchronize
  (JNIEnv *, jobject, jobject, jlong, jboolean);

/*
 * Class:     org_ggf_drmaa_DrmaaJNI
 * Method:    wait
 * Signature: (Ljava/lang/String;J)Lorg/ggf/gridway/drmaa/JobInfo;
 */
JNIEXPORT jobject JNICALL Java_org_ggf_drmaa_DrmaaJNI_wait
  (JNIEnv *, jobject, jstring, jlong);

/*
 * Class:     org_ggf_drmaa_DrmaaJNI
 * Method:    getJobProgramStatus
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_ggf_drmaa_DrmaaJNI_getJobProgramStatus
  (JNIEnv *, jobject, jstring);
  
/*
 * Class:     org_ggf_drmaa_DrmaaJNI
 * Method:    getContact
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_ggf_drmaa_DrmaaJNI_getContact
  (JNIEnv *, jobject);

/*
 * Class:     org_ggf_drmaa_DrmaaJNI
 * Method:    getVersion
 * Signature: ()Lorg/ggf/gridway/drmaa/Version;
 */
JNIEXPORT jobject JNICALL Java_org_ggf_drmaa_DrmaaJNI_getVersion
  (JNIEnv *, jobject);

/*
 * Class:     org_ggf_drmaa_DrmaaJNI
 * Method:    getDRMSInfo
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_ggf_drmaa_DrmaaJNI_getDRMSInfo
  (JNIEnv *, jobject);

/*
 * Class:     org_ggf_drmaa_DrmaaJNI
 * Method:    getDRMAAImplementation
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_ggf_drmaa_DrmaaJNI_getDRMAAImplementation
  (JNIEnv *, jobject);
  
#ifdef __cplusplus
}
#endif
#endif
