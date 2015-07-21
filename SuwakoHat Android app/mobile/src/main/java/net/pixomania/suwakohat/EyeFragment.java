package net.pixomania.suwakohat;

import android.graphics.Color;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.RadioButton;
import android.widget.SeekBar;


public class EyeFragment extends Fragment {

    public static EyeFragment newInstance() {
        return new EyeFragment();
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.fragment_eyes, container, false);

        final RadioButton leftEye = (RadioButton) v.findViewById(R.id.leftEyeRadioBtn);
        final RadioButton rightEye = (RadioButton) v.findViewById(R.id.rightEyeRadioBtn);

        Button button1 = (Button) v.findViewById(R.id.regularEyeBtn);
        button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v1) {
                String eyeMode = "a";
                if (leftEye.isChecked()) eyeMode = "b";
                else if (rightEye.isChecked()) eyeMode = "c";
                MainActivity.getBluetooth().send(eyeMode + "0");
            }
        });

        Button button2 = (Button) v.findViewById(R.id.arrowEyeBtn);
        button2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v1) {
                String eyeMode = "a";
                if (leftEye.isChecked()) eyeMode = "b";
                else if (rightEye.isChecked()) eyeMode = "c";
                MainActivity.getBluetooth().send(eyeMode + "1");
            }
        });

        Button button3 = (Button) v.findViewById(R.id.shutEyeBtn);
        button3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v1) {
                String eyeMode = "a";
                if (leftEye.isChecked()) eyeMode = "b";
                else if (rightEye.isChecked()) eyeMode = "c";
                MainActivity.getBluetooth().send(eyeMode + "2");
            }
        });

        Button button4 = (Button) v.findViewById(R.id.staticEyeBtn);
        button4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v1) {

                MainActivity.getBluetooth().send("d0");
            }
        });

        Button button5 = (Button) v.findViewById(R.id.randomEyeBtn);
        button5.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v1) {

                MainActivity.getBluetooth().send("d1");
            }
        });

        SeekBar brightness = (SeekBar) v.findViewById(R.id.brightness);

        brightness.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                String progress = String.format("%03d", seekBar.getProgress());
                MainActivity.getBluetooth().send("g" + progress);
            }
        });

        Button button6 = (Button) v.findViewById(R.id.nolook);
        button6.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v1) {

                MainActivity.getBluetooth().send("h0");
            }
        });

        Button button7 = (Button) v.findViewById(R.id.dolook);
        button7.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v1) {

                MainActivity.getBluetooth().send("h1");
            }
        });
        return v;
    }
}