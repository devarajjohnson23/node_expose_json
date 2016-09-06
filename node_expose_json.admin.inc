<?php

/**
 * @file
 * Administrative page callbacks for node_expose_json module.
 */

/**
 * [node_expose_json_page description]
 * @return [String] [Return the JSON format of the requested Node]
 */
function node_expose_json_page($type='page',$nid){
  //Check plain since input is from user to sanitize the value
  $type = check_plain($type);
  //Check plain since input is from user to sanitize the value
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

    drupal_json_output($node);
  }else{
    echo "Please enter the numeric value";
    die;
  }
}
