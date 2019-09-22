Feature: Sending and receiving serialized data

  Scenario: Sending short string from one process to another
     Given receiving process is waiting for data
      When sending process sends 'Example string'
      Then receiving process gets 'Example string'
