<template>
<div class="EditOpenedQuestion">
  Nombre de mots :
  <el-input-number v-model="question.nb_words" :min="1" :max="99"></el-input-number>
</div>
</template>

<script>
export default {
  name: 'EditOpenedQuestion',
  props: {
    question: {
      type: Object,
      required: true
    }
  }
}
</script>

<style scoped>
</style>
