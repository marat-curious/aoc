(ns solution
  (:require [clojure.java.io :as io]))

(defn find-digits
  "Find first and last digits in line"
  [line]
  (re-seq #"\d" line))

(defn get-numbers
  "Get sequence of numbers from line"
  [seq]
  (map
    #(+ (* 10 (Integer. (first %))) (Integer. (last %)))
    (map #(find-digits %) seq)))

(defn example
  "Solution of day 01 - part 1 - example"
  [opts]
  (with-open [rdr (io/reader "./example")]
    (println (reduce + (get-numbers (line-seq rdr))))))

(defn input
  "Solution of day 01 - part 1 - input"
  [opts]
  (with-open [rdr (io/reader "./input")]
    (println (reduce + (get-numbers (line-seq rdr))))))
