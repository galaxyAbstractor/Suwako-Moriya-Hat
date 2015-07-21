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

import com.larswerkman.holocolorpicker.ColorPicker;
import com.larswerkman.holocolorpicker.OpacityBar;
import com.larswerkman.holocolorpicker.SVBar;
import com.larswerkman.holocolorpicker.SaturationBar;
import com.larswerkman.holocolorpicker.ValueBar;


public class ColorFragment extends Fragment {

    public static ColorFragment newInstance() {
        return new ColorFragment();
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.fragment_colors, container, false);

        final ColorPicker picker = (ColorPicker) v.findViewById(R.id.picker);
        final SVBar svBar = (SVBar) v.findViewById(R.id.svbar);
        final SaturationBar saturationBar = (SaturationBar) v.findViewById(R.id.saturationbar);
        final ValueBar valueBar = (ValueBar) v.findViewById(R.id.valuebar);

        picker.addSVBar(svBar);
        picker.addSaturationBar(saturationBar);
        picker.addValueBar(valueBar);

        Button button1 = (Button) v.findViewById(R.id.setColor);
        button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v1) {
                picker.setOldCenterColor(picker.getColor());
                String red = String.format("%03d", Color.red(picker.getColor()));
                String green = String.format("%03d", Color.green(picker.getColor()));
                String blue = String.format("%03d", Color.blue(picker.getColor()));


                MainActivity.getBluetooth().send("e" + red + green + blue);
            }
        });

        Button button2 = (Button) v.findViewById(R.id.staticColor);
        button2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v1) {

                MainActivity.getBluetooth().send("f0");
            }
        });

        Button button3 = (Button) v.findViewById(R.id.fading);
        button3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v1) {

                MainActivity.getBluetooth().send("f1");
            }
        });

        Button button4 = (Button) v.findViewById(R.id.random);
        button4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v1) {

                MainActivity.getBluetooth().send("f2");
            }
        });


        return v;
    }
}