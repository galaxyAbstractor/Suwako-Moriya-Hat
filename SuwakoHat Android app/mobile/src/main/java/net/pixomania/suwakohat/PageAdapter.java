package net.pixomania.suwakohat;

import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;

public class PageAdapter extends FragmentPagerAdapter {
    private final String[] TITLES = { "Eyes", "Color" };

    public PageAdapter(FragmentManager fm) {
        super(fm);
    }
    @Override
    public CharSequence getPageTitle(int position) {
        return TITLES[position];
    }
    @Override
    public int getCount() {
        return TITLES.length;
    }
    @Override
    public Fragment getItem(int position) {
        return EyeFragment.newInstance(position);
    }
}
