<?php

/**
 * @file
 * Administrative page callbacks for node_expose_json module.
 */

/**
 * Query the Node for the respective Node type and return the JSON value of node
 * @param  string $type Bundle name = Content type name
 * @param  int $nid  Node ID of the particular Content type
 * @return string $node Return the JSON format of the requested Node
 */
function node_expose_json_page($type='page',$nid){
  //Check plain $type since input is from user to sanitize the value
  $type = check_plain($type);
  //Check plain $nid since input is from user to sanitize the value and check if
  //it is numeric or not
  $nid = check_plain($nid) && is_numeric($nid) ? $nid : FALSE;
  if($nid){
    //Entity Query Entity type = node, Bundle = Node Type, Nid = Node ID
    $query = new EntityFieldQuery();
    $result = $query->entityCondition('entity_type', 'node')
                    ->entityCondition('bundle', $type)
                    ->propertyCondition('nid', $nid)
                    ->execute();
    if(isset($result) && !empty($result)){
      $node = node_load_multiple(array_keys($result['node']));
    }
    //Show the JSON data if the node exist otherwise show 403 access denied
    $node = !empty($node) ? $node : drupal_access_denied();
    //Return the data as JSON using drupal default function
    drupal_json_output($node);
  }else{
    echo "Please enter the numeric value";
    die;
  }
}
