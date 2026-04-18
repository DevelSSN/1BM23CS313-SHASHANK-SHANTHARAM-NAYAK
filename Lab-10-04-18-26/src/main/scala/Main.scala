import org.apache.spark.sql.SparkSession

object WordCountFiltered {
  def main(args: Array[String]): Unit = {

    val spark = SparkSession.builder()
      .appName("WordCountFiltered")
      .master("local[*]")
      .getOrCreate()
    
    spark.sparkContext.setLogLevel("ERROR")
    val sc = spark.sparkContext

    val textFile = sc.textFile("sparkdata.txt")

    // Step 1: full word count
    val wordCounts = textFile
      .flatMap(_.toLowerCase.split("\\W+"))
      .filter(_.nonEmpty)
      .map(word => (word, 1))
      .reduceByKey(_ + _)

    // =========================
    // PRINT ALL WORD COUNTS
    // =========================
    println("\n===== ALL WORD COUNTS =====")
    wordCounts.collect()
      .sortBy(-_._2)
      .foreach { case (word, count) =>
        println(s"$word -> $count")
      }

    // Step 2: filter > 4
    val filtered = wordCounts
      .filter { case (_, count) => count > 4 }
      .sortBy({ case (_, count) => count }, ascending = false)

    // =========================
    // PRINT FILTERED COUNTS (>4)
    // =========================
    println("\n===== WORDS WITH COUNT > 4 =====")
    filtered.collect().foreach {
      case (word, count) =>
        println(s"$word -> $count")
    }

    spark.stop()
  }
}
