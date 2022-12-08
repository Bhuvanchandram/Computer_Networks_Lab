/*Java program to implement token bucket algorithm*/
import java.util.Scanner;
public class Main{
        public static void main(String[] args){
            Scanner s=new Scanner(System.in);
            int bucket_size,input_rate,output_rate,time_steps,current_size=0;
            System.out.print("Enter the bucket size: ");
            bucket_size=s.nextInt();
            System.out.print("\nEnter input rate: ");
            input_rate=s.nextInt();
            System.out.print("\nEnter output rate: ");
            output_rate=s.nextInt();
            System.out.println("Enter the steps to simulate: ");
            time_steps=s.nextInt();
            for(int i=0;i<time_steps;i++){
                int space_left=bucket_size-current_size;
                int loss=0;
                if(input_rate<=space_left){
                    current_size+=input_rate;
                }else{
                    loss=input_rate-space_left;
                    current_size=bucket_size;
                }
                current_size-=output_rate;
                System.out.print("\n");
                System.out.println("Time= "+i+"s | Bucket/Buffer status: "+current_size+"/"+bucket_size+", Packet loss = "+loss);
            }
            s.close();
        }
}
