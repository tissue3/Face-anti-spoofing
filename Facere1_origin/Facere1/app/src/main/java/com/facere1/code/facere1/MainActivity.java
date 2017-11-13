cpackage com.facere1.code.facere1;

import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URI;
import java.net.URISyntaxException;


public class MainActivity extends Activity implements View.OnClickListener{
    String fileStr = "training_set.txt";
    String operatePath ;
    public static native float ImgFun(String imgPath,String textPath);
        static {
               System.loadLibrary("ImgFun");
           }
    int REQUEST_CODE_PICK_IMAGE = 0x1001;
    int REQUEST_CODE_CAPTURE_CAMEIA = 0x1002;
    ImageView iv;
    Button btn_cam,btn_ph;
    TextView tv_result;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        iv = (ImageView) findViewById(R.id.iv);
        btn_cam  = (Button) findViewById(R.id.btn_cam);
        btn_ph  = (Button) findViewById(R.id.btn_ph);
        tv_result = (TextView) findViewById(R.id.tv_result);
        btn_ph.setOnClickListener(this);
        btn_cam.setOnClickListener(this);
        writeToLocal();
//        getImageFromAlbum();
//        getImageFromCamera();

    }


    private void writeToLocal(){
        try {
            //Return an AssetManager instance for your application's package
            InputStream is = getAssets().open("training_set.txt");

             int b = 0;
            File file=new File(Environment.getExternalStorageDirectory(), fileStr);
            operatePath = file.getAbsolutePath();
            if(file.exists()){
                return;
            }
            FileOutputStream fis = new FileOutputStream(file);
            Log.e("filePa",file.getAbsolutePath());
            while((b=is.read())!=-1){
                 fis.write(b);
            }

        } catch (IOException e) {
            // Should never happen!
            e.printStackTrace();
        }
    }





    protected void getImageFromAlbum() {
        Intent intent = new Intent(Intent.ACTION_PICK);
        intent.setType("image/*");//相片类型
        startActivityForResult(intent, REQUEST_CODE_PICK_IMAGE);
    }
    File tempFile;
    String PHOTO_FILE_NAME = "";
    protected void getImageFromCamera() {
        String state = Environment.getExternalStorageState();
        if (state.equals(Environment.MEDIA_MOUNTED)) {
//            Intent getImageByCamera = new Intent("android.media.action.IMAGE_CAPTURE");
//            PHOTO_FILE_NAME = "test"+System.currentTimeMillis()+".jpg";
//            tempFile = new File(Environment.getExternalStorageDirectory(),
//                    PHOTO_FILE_NAME);
//            // 从文件中创建uri
//            Uri uri = Uri.fromFile(tempFile);
//            getImageByCamera.putExtra(MediaStore.EXTRA_OUTPUT, uri);
//
//            startActivityForResult(getImageByCamera, REQUEST_CODE_CAPTURE_CAMEIA);
            Intent getImageByCamera = new Intent("android.media.action.IMAGE_CAPTURE");
            startActivityForResult(getImageByCamera, REQUEST_CODE_CAPTURE_CAMEIA);
        }
        else {
            Toast.makeText(getApplicationContext(), "请确认已经插入SD卡", Toast.LENGTH_LONG).show();
        }
    }

    String  cameraPath ;

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == REQUEST_CODE_PICK_IMAGE) {
               try{
                   String[] proj = {MediaStore.Images.Media.DATA};

                   //好像是android多媒体数据库的封装接口，具体的看Android文档
                   Cursor cursor = managedQuery(data.getData(), proj, null, null, null);
                   //按我个人理解 这个是获得用户选择的图片的索引值
                   int column_index = cursor.getColumnIndexOrThrow(MediaStore.Images.Media.DATA);
                   //将光标移至开头 ，这个很重要，不小心很容易引起越界
                   cursor.moveToFirst();
                   //最后根据索引值获取图片路径
                   String path = cursor.getString(column_index);
                   Log.e("path",path);
                   iv.setImageBitmap(BitmapFactory.decodeFile(path));
                float x =    ImgFun(path,operatePath);
                   Log.e("x",x+"    ----");
                   setResult(x);
               }catch (Exception e){
                    e.printStackTrace();
               }
            }
        else{
            Uri uri = data.getData();
            if(uri == null){
                //use bundle to get data
                Bundle bundle = data.getExtras();
                if (bundle != null) {
                    Bitmap  photo = (Bitmap) bundle.get("data"); //get bitmap
                    //spath :生成图片取个名字和路径包含类型
                    File file1=new File(Environment.getExternalStorageDirectory(), System.currentTimeMillis()/1000+".jpg");
                    cameraPath = file1.getAbsolutePath();
                    saveImage(photo, cameraPath);
                    iv.setImageBitmap(BitmapFactory.decodeFile(cameraPath));
                    float x =    ImgFun(cameraPath,operatePath);
                    Log.e("x",x+"    ----");
                    setResult(x);
                } else {
                    Toast.makeText(getApplicationContext(), "err****", Toast.LENGTH_LONG).show();
                    return;
                }
            }else{
                try{
                    String[] proj = {MediaStore.Images.Media.DATA};

                    //好像是android多媒体数据库的封装接口，具体的看Android文档
                    Cursor cursor = managedQuery(data.getData(), proj, null, null, null);
                    //按我个人理解 这个是获得用户选择的图片的索引值
                    int column_index = cursor.getColumnIndexOrThrow(MediaStore.Images.Media.DATA);
                    //将光标移至开头 ，这个很重要，不小心很容易引起越界
                    cursor.moveToFirst();
                    //最后根据索引值获取图片路径
                    String path = cursor.getString(column_index);
                    Log.e("path",path);
                    float x =    ImgFun(path,operatePath);
                    iv.setImageBitmap(BitmapFactory.decodeFile(path));
                    Log.e("x",x+"    ----");
                    setResult(x);
                }catch (Exception e){
                    e.printStackTrace();
                }
            }
        }
          }

    public void setResult(float x){
        if(x ==1){
            tv_result.setText("返回结果为 "+ x +"是拍的人脸");
        }else{
            tv_result.setText("返回结果为 "+ x +"是拍的照片");
        }
    }

    public static void saveImage(Bitmap photo, String spath) {
        try {
            BufferedOutputStream bos = new BufferedOutputStream(
                    new FileOutputStream(spath, false));
            photo.compress(Bitmap.CompressFormat.JPEG, 100, bos);
            bos.flush();
            bos.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public void onClick(View view) {
        switch (view.getId()){
            case R.id.btn_cam:
                getImageFromCamera();
                break;
            case R.id.btn_ph:
                getImageFromAlbum();
                break;
        }
    }
}
