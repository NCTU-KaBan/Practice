
// @EXPECTED_RESULTS@: CORRECT

import java.util.*;
import java.io.*;
import java.math.*;

public class EdgeCase {
  public static void main(String[] args){
    int i;
    Scanner in = new Scanner(System.in);
    BigInteger[] Lucas = new BigInteger[10001];
    Lucas[1] = BigInteger.valueOf(1);
    Lucas[2] = BigInteger.valueOf(3);
    for( i = 3 ;i<=10000;i++)
      Lucas[i] = Lucas[i-1].add(Lucas[i-2]);

    while(in.hasNextInt()){
      int n = in.nextInt();
      System.out.println(Lucas[n]);
    }
  }
}
