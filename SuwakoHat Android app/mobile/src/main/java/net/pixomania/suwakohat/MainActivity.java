package net.pixomania.suwakohat;

import android.support.v4.view.ViewPager;
import android.os.Bundle;
import android.util.TypedValue;
import android.view.Menu;
import android.view.MenuItem;
import android.support.v4.app.FragmentActivity;

import com.astuetz.PagerSlidingTabStrip;


public class MainActivity extends FragmentActivity  {

    private PagerSlidingTabStrip tabs;
    private ViewPager pager;

    private static Bluetooth mBluetooth;

    public static Bluetooth getBluetooth() {
        return mBluetooth;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Initialize the ViewPager and set an adapter
        pager = (ViewPager) findViewById(R.id.pager);
        pager.setAdapter(new PageAdapter(getSupportFragmentManager()));

        final int pageMargin = (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 4, getResources()
                .getDisplayMetrics());
        pager.setPageMargin(pageMargin);

        // Bind the tabs to the ViewPager
        tabs = (PagerSlidingTabStrip) findViewById(R.id.tabs);
        tabs.setIndicatorColor(0xFFFFBB00);
        tabs.setViewPager(pager);

        mBluetooth = new Bluetooth(getApplicationContext());
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    // OnResume, called right before UI is displayed. Start the BTLE connection.
    @Override
    protected void onResume() {
        super.onResume();

        mBluetooth.connect();
    }

    @Override
    protected void onStop() {
        super.onStop();

        mBluetooth.disconnect();
    }

}
