## dynamo

### Objective:

Dispatch work to agents. 

### Interface: 
```
batch.hook( function ) -> agent 
batch.invoke( ... )
batch.kill( ... )
batch.kill_invoke( ... )
batch.is_dead()
```
### Dependencies

Dynamo uses Circuit for thread syncronization

### Plan

Instead of copy and insert elements inside of invok, push the elements one by one as they get traversed (obviosly don't add elements that are dead)...

![doc header](https://s3-us-west-2.amazonaws.com/mod-resources/mod-header.svg)
