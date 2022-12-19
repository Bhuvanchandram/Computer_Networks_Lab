import java.math.BigInteger;
import java.util.Random;
import java.util.Scanner;

public class RSA {
    private BigInteger p;
    private BigInteger q;
    private BigInteger n;
    private BigInteger phi;
    private BigInteger e;
    private BigInteger d;
    private int bitlength = 1024;
    private Random r;
    

    public RSA() {
        r = new Random();
        p = BigInteger.probablePrime(bitlength, r);
        q = BigInteger.probablePrime(bitlength, r);
        n = p.multiply(q);
        phi = p.subtract(BigInteger.ONE).multiply(q.subtract(BigInteger.ONE));
        e = BigInteger.probablePrime(bitlength / 2, r);
        while (phi.gcd(e).compareTo(BigInteger.ONE) > 0 && e.compareTo(phi) < 0) {
            e.add(BigInteger.ONE);
        }
        d = e.modInverse(phi);
    }

    public RSA(BigInteger e, BigInteger d, BigInteger n) {
        this.e = e;
        this.d = d;
        this.n = n;
    }

    public BigInteger[] encrypt(String message) {
        BigInteger[] encrypted = new BigInteger[message.length()];
        for (int i = 0; i < message.length(); i++) {
            encrypted[i] = new BigInteger(new byte[] { (byte) message.charAt(i) });
            encrypted[i] = encrypted[i].modPow(e, n);
        }
        return encrypted;
    }

    public String decrypt(BigInteger[] encrypted) {
        StringBuilder decrypted = new StringBuilder();
        for (BigInteger anEncrypted : encrypted) {
            BigInteger m = anEncrypted.modPow(d, n);
            decrypted.append((char) m.intValue());
        }
        return decrypted.toString();
    }

    public static void main(String[] args) {
        RSA rsa = new RSA();
        System.out.print("Enter the message to be encrypted: ");
        Scanner in = new Scanner(System.in);
        String message = in.nextLine();
        System.out.println("Original message: " + message);
        BigInteger[] encrypted = rsa.encrypt(message);
        String decrypted = rsa.decrypt(encrypted);
        System.out.println("\nDecrypted message: " + decrypted);
    }
}
