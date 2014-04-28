import java.io.*;
class Retrieve {
	private native void retrieve(String imgn);
	public static void main(String[] args) {
		Retrieve ex = new Retrieve();
		BufferedReader ir = new BufferedReader(new InputStreamReader(System.in));
		String imgn=null;
		try {
			imgn=ir.readLine();
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		ex.retrieve(imgn);
	}
	static {
		System.loadLibrary("Retrieve");
	}
}