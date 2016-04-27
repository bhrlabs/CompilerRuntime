import java.util.ArrayList;
import java.util.List;

/**
 * SER 502 Project 2 Group 31.
 * 
 * Flash Programming Language
 * 
 * Class corresponding to function definition.
 * 
 */
public class Function {

	String name;
	int lineNum;
	List<String> params;
	ArrayList<String> linesOfCode;
	
	public Function(String name, int lineNum, List<String> params, ArrayList<String> linesOfCode){
		this.name  = name;
		this.lineNum = lineNum;
		this.params = params;
		this.linesOfCode = linesOfCode;
	}
	
	@Override
	public String toString(){
		String str = "Name of Function:"+name+"\n"+"with parameters:"+params.toString()+" \nand lines of code:"+linesOfCode.toString()+"\n";
		return str;
	}
	
	public String getParams(){
		String p = "";
		for(String s:this.params){
			p = p.concat(s+",");
		}
		return p.substring(0, p.length());
	}
}
