import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;

// @EXPECTED_RESULTS@: CORRECT

public class JointVenture {

    private static Boolean fromFile = false;
    private static Scanner input;

    public static void main(String[] args) {

        if(true == fromFile) {
            try {
                input = new Scanner(new File("legos.in"));
            } catch (FileNotFoundException e) {
                // Forgot we need to read from inputstream
                input = new Scanner(System.in);
            }
        } else {
            input = new Scanner(System.in);
        }

        while(input.hasNextInt()) {
            doCase();
        }
    }

    private static void doCase() {

        int opening = input.nextInt() * 10000000;
        int numLegos = input.nextInt();
        int[] legos = new int[numLegos];

        for(int i = 0; i < numLegos; i++) {
            legos[i] = input.nextInt();
        }

        Arrays.sort(legos);

        int left = 0;
        int right = numLegos-1;

        while(left < right) {

            if(legos[left] + legos[right] == opening) {
                System.out.println("yes " + legos[left] + " " + legos[right]);
                return;
            } else if(legos[left] + legos[right] < opening) {
                left++;
            } else {
                right--;
            }
        }

        System.out.println("danger");
        return;
    }

}
