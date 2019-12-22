Feature: Protobuf usage with ATL

  Scenario Outline: Calculating exponentiation using two ATL endpoints - server and client
     Given Exponentiation server is running
      When Exponentiation clients sends base <base> and exponent <exponent>
      Then Exponentiation client receives <result>

   Examples:
   | base | exponent | result |
   |   2  |    10    |  1024  |
   |   3  |     4    |    81  |
   |  11  |     2    |   121  |
