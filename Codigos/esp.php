<?php
//declaracion de variables
$Corriente=	$_GET['corriente'];
$Potencia =$_GET['potencia'];

//imprime los datos en el servidor
echo "La corriente es: ".$Corriente."<br>La potencia es: ".$Potencia;

//variables para la conexion a bd
$usuario="root";
$contraseña="";
$servidor="localhost";
$basededatos="proyectoarduino";//nombre de la base da datos

$conexion =mysqli_connect($servidor, $usuario, "") or die ("No se ha podido conectar a la base de datos");
$db= mysqli_select_db($conexion, $basededatos) or die ("No se ha podido conectar a la base de datos");

$consulta= "INSERT INTO datoscircuito (Corriente,Potencia) VALUES (".$Corriente.",".$Potencia.")";

$resultado= mysqli_query($conexion, $consulta);
?>