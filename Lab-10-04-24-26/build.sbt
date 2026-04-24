name := "WordCountFiltered"

version := "0.1"

scalaVersion := "2.13.12"

val sparkVersion = "3.5.1"

libraryDependencies ++= Seq(
  "org.apache.spark" %% "spark-core" % sparkVersion,
  "org.apache.spark" %% "spark-sql"  % sparkVersion
)
scalaInstance := {
  val inst = (scalaInstance).value
  inst
}

classLoaderLayeringStrategy := ClassLoaderLayeringStrategy.Flat
