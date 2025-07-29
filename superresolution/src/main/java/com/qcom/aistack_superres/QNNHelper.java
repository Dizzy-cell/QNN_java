package com.qcom.aistack_superres;

import static android.graphics.Color.rgb;

import android.app.Application;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.util.Log;

import org.opencv.android.Utils;
import org.opencv.core.Mat;

public class QNNHelper {
    private final Application mApplication;
    private AssetManager assetManager;

    private float infer_time=0;

    // Constructor
    public QNNHelper(Application application) {
        mApplication = application;
    }
    public float getInfer_time()
        {return infer_time;}

    //Native functions
    public native String queryRuntimes(String backend);
    public native String initQNN(AssetManager assetManager, String backend, String model_name,String nativeDirPath);
    public native float inferQNN(long inputmataddress, long outputmataddress);

    /**
     * This method loads ML models on selected runtime
     */
    public boolean loadingMODELS(String runtime_var, String model_name) {

        assetManager = mApplication.getAssets();
        String nativeDirPath = mApplication.getApplicationInfo().nativeLibraryDir;
        String res_query = queryRuntimes(nativeDirPath);
        System.out.println(res_query);
        String[] path = {"./"};
//        assetManager.list(path);
//        System.out.println("list--sumith:"+);
        Log.e("QNN_INF", "initQNN()");
        String init_str = initQNN(assetManager, runtime_var, model_name,nativeDirPath);
        System.out.println("RESULT:"+init_str);
        Log.e("QNN_INF", "RESULT:"+init_str);

        int success_count = init_str.split("success", -1).length -1;

        if(success_count==1)
        {
            System.out.println("Model built successfully");
            return true;
        }

        return false;
    }

    /*
        This method makes inference on bitmap.
    */
    public Bitmap qnnInference(Bitmap modelInputBitmap) {

        try{

            Log.e("QNN_INF", "perpare input()");

            Mat inputMat = new Mat();
            Utils.bitmapToMat(modelInputBitmap, inputMat);

            Mat outputMat = new Mat();

            Log.e("QNN_INF", "inferQNN()");

            infer_time = inferQNN(inputMat.getNativeObjAddr(), outputMat.getNativeObjAddr());


            if(infer_time==0.0)
                System.out.println("ERROR");
            else
            {
                Bitmap outputBitmap =  Bitmap.createBitmap(outputMat.cols(), outputMat.rows(), Bitmap.Config.ARGB_8888);
                Utils.matToBitmap(outputMat,outputBitmap);
                return outputBitmap;
            }
        }catch (Exception e) {
                e.printStackTrace();
             Log.e("QNN_INF", "error()");
        }
        return null;
    }


}