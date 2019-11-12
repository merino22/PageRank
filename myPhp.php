
<?php

if($_POST['busqueda']){
	#code
	$texto = $_POST['busqueda'];
	system("C:\\xampp\\htdocs\\PageRank.exe $texto");
	//$file=fopen("Search.html","r") or die("C PILLIN");
	//echo file_get_contents($file);
	//($file,filesize("Search.html"));
	//fclose($file);

	$file = fopen("SearchF.html","r");
	echo fgets($file);
	fclose($file);

}
?>