// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from dependency_evaluator.djinni

package com.example.sankar_5526.helloworld;

import java.util.ArrayList;

public final class MyRecord {


    /*package*/ final int mKey1;

    /*package*/ final String mKey2;

    /*package*/ final ArrayList<ArrayList<String>> mKey3;

    public MyRecord(
            int key1,
            String key2,
            ArrayList<ArrayList<String>> key3) {
        this.mKey1 = key1;
        this.mKey2 = key2;
        this.mKey3 = key3;
    }

    public int getKey1() {
        return mKey1;
    }

    public String getKey2() {
        return mKey2;
    }

    public ArrayList<ArrayList<String>> getKey3() {
        return mKey3;
    }

    @Override
    public String toString() {
        return "MyRecord{" +
                "mKey1=" + mKey1 +
                "," + "mKey2=" + mKey2 +
                "," + "mKey3=" + mKey3 +
        "}";
    }

}