<?php

/**
 * Generates a page that contains the taxonomy view.
 */
function tripal_phylogeny_taxonomy_view() {
  $values = array(
    'type_id' => array(
      'name' => 'taxonomy',
    ),
  );

  $message = t('Site administrators:  This page is meant to provide
      a heirarchical taxonomic tree for all of the organism present
      in this site.  This may not be useful if you only have a few
      species. If so, you can turn off this page by disabling this page on
      the site\'s <a href="@menu">Navigation Menu</a>.  Otherwise, to generate the taxonomy go to this site\'s
      <a href="@taxloader">NCBI taxonomy loader</a> to import the taxonomy information from NCBI.
      <br><br>Note: If you add new species to this site, you should rerun the
        NCBI taxonomy loader to update the view</p>',
      array(
        '@menu' => url('admin/structure/menu/manage/navigation'),
        '@taxloader' => url('admin/tripal/loaders/chado_taxonomy'
      ))
  );
  $admin_message = tripal_set_message($message, TRIPAL_INFO, array('return_html' => TRUE));

  $content['admin_message'] = array(
    '#type' => 'markup',
    '#markup' => t('This site has not yet prepared the taxonomy for viewing.') . $admin_message,
  );

  $phylotree = chado_generate_var('phylotree', $values);
  if ($phylotree) {
    $node = new stdClass();
    $node->phylotree = $phylotree;

    $phylotree = chado_expand_var($phylotree,'field','phylotree.comment');
    module_load_include('inc', 'tripal_chado', 'includes/tripal_chado.phylotree');
    tripal_phylogeny_prepare_tree_viewer($phylotree);

    if ($phylotree->type_id->name == "taxonomy" and $phylotree->has_nodes) {
      $content['comment'] = array(
        '#type' => 'markup',
        '#markup' =>$phylotree->comment
      );
      $ajax_loader = url(drupal_get_path('module', 'tripal') . '/theme/images/ajax-loader.gif');
      $content['phylogram'] = array(
        '#type' => 'markup',
        '#markup' => '
          <div id="phylogram">
            <img src="' . $ajax_loader . '" class="phylogram-ajax-loader"/>
          </div>
        '
      );
    }
  }

  return $content;
}

