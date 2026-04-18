import scala.io.Source

object WordCount {
  def main(args: Array[String]): Unit = {

    val words = Source.fromFile("sparkdata.txt")
      .mkString
      .toLowerCase
      .split("\\s+")
      .filter(_.nonEmpty)

    val wordCount = words
      .groupBy(identity)
      .map { case (word, list) => (word, list.length) }

    wordCount.foreach {
      case (word, count) => println(s"$word -> $count")
    }
  }
}
