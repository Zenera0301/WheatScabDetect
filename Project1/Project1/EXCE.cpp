#include<stdio.h>
public DataSet ExcelToDS(string Path)
{
	string strConn = "Provider=Microsoft.Jet.OLEDB.4.0;" + "Data Source=" + Path + ";" + "Extended Properties=Excel 8.0;";
	OleDbConnection conn = new OleDbConnection(strConn);
	conn.Open();
	string strExcel = "";
	OleDbDataAdapter myCommand = null;
	DataSet ds = null;
	strExcel = "select * from [sheet1$]";
	myCommand = new OleDbDataAdapter(strExcel, strConn);
	ds = new DataSet();
	myCommand.Fill(ds, "table1");
	return ds;
}