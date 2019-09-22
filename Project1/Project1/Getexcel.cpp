/// <summary>  
/// 选择相应的Excel文件  
/// </summary>  
/// <param name="sender"></param>  
/// <param name="e"></param>  
private void btn1_Click(object sender, EventArgs e)
{
	try
	{
		//获取Excel文件路径和名称  
		OpenFileDialog odXls = new OpenFileDialog();
		// 指定相应的打开文档的目录  
		odXls.InitialDirectory = "C://";
		// 设置文件格式  
		odXls.Filter = "Excel files (*.xls)|*.xls";
		odXls.FilterIndex = 2;
		odXls.RestoreDirectory = true;
		if (odXls.ShowDialog() == DialogResult.OK)
		{
			txtFilePath.Text = odXls.FileName;
			OleDbConnection oledbConn = null;
			string sConnString = "provider=Microsoft.Jet.OLEDB.4.0;data source=" + odXls.FileName + ";Extended Properties=Excel 5.0;Persist Security Info=False";
			oledbConn = new OleDbConnection(sConnString);
			oledbConn.Open();
			DataTable dt = oledbConn.GetOleDbSchemaTable(OleDbSchemaGuid.Tables, new object[] { null, null, null, "TABLE" });
			combox1.Items.Clear();
			foreach(DataRow dr in dt.Rows)
			{
				combox1.Items.Add((String)dr["TABLE_NAME"]);
			}
			if (combox1.Items.Count > 0)
				combox1.SelectedIndex = 0;
		}
	}
	catch (Exception Ex)
	{
		MessageProcess.ShowError(Ex.Message);
	}
}
/// <summary>  
///  读取相应的表名的Excel文件中数据到当前DataGridview中显示  
/// </summary>  
/// <param name="sender"></param>  
/// <param name="e"></param>  
private void btn2_Click(object sender, EventArgs e)
{
	OleDbConnection ole = null;
	OleDbDataAdapter da = null;
	DataTable dt = null;
	string strConn = "Provider=Microsoft.Jet.OLEDB.4.0;"
		+ "Data Source=" + txtFilePath.Text.Trim() + ";"
		+ "Extended Properties=Excel 5.0";
	string sTableName = combox1.Text.Trim();
	string strExcel = "select * from [" + sTableName + "]";
	try
	{
		ole = new OleDbConnection(strConn);
		ole.Open();
		da = new OleDbDataAdapter(strExcel, ole);
		dt = new DataTable();
		da.Fill(dt);
		this.xlsExpData.DataSource = dt;
		for (int i = 0; i < dt.Columns.Count; i++)
		{
			xlsExpData.Columns[i].AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
		}
		ole.Close();
	}
	catch (Exception Ex)
	{
		MessageBox.Show(Ex.Message);
	}
	finally
	{
		if (ole != null)
			ole.Close();
	}
}