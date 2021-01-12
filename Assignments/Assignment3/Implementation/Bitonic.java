public class Bitonic {
	Bitonic[] half;
	Merger merger;
	int width;
	public Bitonic(int myWidth) {
		width=myWidth;
		merger=new Merger(width);
		if (width>2) {
			half=new Bitonic[] {new Bitonic(width/2),new Bitonic(width/2)};
		}
	}
	public int traverse(int input) {
		int output=0;
		if(width>2) {
			output=half[input/(width/2)].traverse(input/2);
		}
		return merger.traverse(output/(width/2)*(width/2)+width);
	}
	public static void main(String[] args) 
	{
		Bitonic mad=new Bitonic(16);	
		for(int i=0;i<16;i++)
		{
			mad.traverse(i);
		}
	}
}
class Balancer {
	Boolean toggle=true;
	public synchronized int traverse(int t){
		try {
			if(toggle) {
				return 0;
			} else{
				return 1;
			}
		}
		finally {
			toggle=!toggle;
		}
	}
}

class Merger {
	Merger[] half;
	Balancer[] layer;
	final int width;
	public Merger(int myWidth) {
		width=myWidth;
		layer=new Balancer[width/2];
		for(int i=0;i<width/2;i++)
		{
			layer[i]=new Balancer();
		}
		if(width>2) {
			half=new Merger[]{new Merger(width/2),new Merger(width/2)};
		}
	}
	public int traverse(int input) {
		int output=0;
		if(input < width/2) {
			output=half[input%2].traverse(input/2);
		} else {	
			output=half[1-(input%2)].traverse(input/2);
		}
		return output;
	}
}
